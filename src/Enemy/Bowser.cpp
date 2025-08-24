#include "Enemy/Bowser.h"
#include <cmath>
#include <iostream>

Bowser::Bowser(Vector2 pos, Player *&player, std::vector<Enemy *> &enemies)
	: Enemy(pos, {0, 0}, 1000.0f),
	  state_(Bowser_State::normal),
	  previous_frame_pos(pos),
	  hp_(12),
	  fire_cooldown_(0.0f),
	  fire_timer(0.0f),
	  is_firing_(false),
	  is_jumping_(false),
	  jump_cooldown_(0.0f),
	  enemies_(enemies),
	  target_player_(player)
{
	animation_ = Animation(&Bowser_Sprite::bowser_, Bowser_Sprite::normal_::normal_, 1 / 4.0f);
	score = 10000;
	// TODO: Khởi tạo animation cho fire_animation_, walk_animation_, die_animation_
}

void Bowser::Update(float dt)
{
	previous_frame_pos = position_;

	// dying state

	if (state_ == Bowser_State::dying)
	{
		Be_Dying(dt);
		return;
	}

	// Luôn giảm cooldown mỗi frame
	if (fire_cooldown_ > 0)
		fire_cooldown_ -= dt;
	if (jump_cooldown_ > 0)
		jump_cooldown_ -= dt;

	// State chuyển đổi giữa normal <-> fire
	if (state_ == Bowser_State::normal)
	{
		// Hành động khi ở trạng thái bình thường
		AI_jump();
		velocity_.y += gravity_ * dt;
		position_.y += velocity_.y * dt;
		// Điều kiện chuyển sang fire
		if (fire_cooldown_ <= 0)
		{
			state_ = Bowser_State::fire;
			animation_.Set_Frames(Bowser_Sprite::fire_::fire_);
			fire_timer = 0.0f;
			enemies_.push_back(new LaserFire({position_.x, position_.y - 50.0f}, target_player_->getPosition()));
		}
	}
	else if (state_ == Bowser_State::fire)
	{
		// Hành động khi ở trạng thái bắn
		// Có thể cho phép nhảy khi fire nếu muốn: AI_jump();
		velocity_.y += gravity_ * dt;
		position_.y += velocity_.y * dt;
		fire_timer += dt;
		// Điều kiện chuyển lại normal
		if (fire_timer >= 0.5f)
		{
			state_ = Bowser_State::normal;
			animation_.Set_Frames(Bowser_Sprite::normal_::normal_);
			fire_timer = 0.0f;
			fire_cooldown_ = 2.0f; // reset cooldown bắn
		}
	}
	Move_(dt);
	Animate_();
}

void Bowser::Move_(float dt)
{
	if (!target_player_)
		return;
	float dx = target_player_->getPosition().x - position_.x;
	float speed = 80.0f;
	if (std::abs(dx) > 2.0f)
	{
		velocity_.x = (dx > 0) ? speed : -speed;
		position_.x += velocity_.x * dt;
		if ((velocity_.x > 0 && !face_right_) || (velocity_.x < 0 && face_right_))
		{
			face_right_ = !face_right_;
		}
	}
	else
	{
		velocity_.x = 0;
		// Không đổi face_right_, giữ nguyên hướng cũ
	}
	if (position_.x < x_min_)
		position_.x = x_min_;
	if (position_.x > x_max_)
		position_.x = x_max_;
}

void Bowser::AI_jump()
{
	if (!target_player_)
		return;
	float dx = target_player_->getPosition().x - position_.x;
	bool player_in_range = std::abs(dx) < detect_range_;
	bool player_jumping = !target_player_->Get_isGround();
	if (player_in_range && player_jumping && is_ground && jump_cooldown_ <= 0)
	{
		velocity_.y = -jump_power_;
		is_ground = false;
		jump_cooldown_ = jump_cooldown_duration_; // cooldown nhảy 3 giây
	}
}

void Bowser::Animate_()
{
	// Chọn animation theo state
	animation_.Update(GetFrameTime());
}

void Bowser::Be_Dying(float dt)
{
	dying_time_ += dt;
	if (dying_time_ < dying_up)
	{
		position_.y -= jump_power_ * dt;
	}
	else if (dying_time_ < dying_down)
	{
		position_.y += jump_power_ * dt * 2.0f;
	}
	else if (dying_time_ >= dying_down)
	{
		is_active = false;
	}
	is_dead = true;
}

void Bowser::Draw() const
{
	Rectangle rec__ = {animation_.Get_Current_Rec().x, animation_.Get_Current_Rec().y, face_right_ ? -1.0f * animation_.Get_Current_Rec().width : animation_.Get_Current_Rec().width, animation_.Get_Current_Rec().height};
	float draw_width = animation_.Get_Current_Rec().width * scale_screen;
	float draw_height = animation_.Get_Current_Rec().height * scale_screen;
	Rectangle dest_rec = {position_.x, position_.y, draw_width, draw_height};
	Vector2 origin = {draw_width / 2.0f, draw_height};
	DrawTexturePro(animation_.Get_Sprite().sprite, rec__, dest_rec,
				   {origin.x, origin.y}, // Điểm neo ở giữa
				   0.0f, WHITE);
}

void Bowser::Set_Pos(Vector2 pos)
{
	position_ = pos;
}

Vector2 Bowser::Get_Previous_Pos() const
{
	return previous_frame_pos;
}

void Bowser::Notify_Fall(float dt)
{
	if (is_ground && state_ != Bowser_State::dying)
	{
		is_ground = false;
	}
}

void Bowser::Notify_On_Ground()
{
	if (state_ != Bowser_State::dying)
	{
		is_ground = true;
		velocity_.y = 0.0f;
	}
}

void Bowser::Notify_Be_Fired_Or_Hit()
{
	if (state_ == Bowser_State::dying)
		return;
	hp_ -= 3;
	if (hp_ <= 0 && state_ != Bowser_State::dying)
	{
		is_dead = 1;
		state_ = Bowser_State::dying;
		animation_.Set_Frames(Bowser_Sprite::dying_::dying_);
	}
	std::cout << "[Bowser] Hit or fire! HP: " << hp_ << "\n";
}

bool Bowser::Can_Be_Stomped() const
{
	return false;
}

bool Bowser::Can_Be_Fired_Or_Hit() const
{
	return state_ != Bowser_State::dying;
}

json Bowser::to_json() const
{
	return {
		{"x", position_.x},
		{"y", position_.y},
		{"vx", velocity_.x},
		{"vy", velocity_.y},
		{"hp", hp_},
		{"state", static_cast<int>(state_)},
		{"score", score},
		{"fire_cooldown", fire_cooldown_},
		{"jump_cooldown", jump_cooldown_},
		{"face_right", face_right_},
		{"dying_time", dying_time_},
		{"is_active", is_active},
		{"is_dead", is_dead},
		{"is_ground", is_ground},
		{"first_appear", first_appear},
		{"animation", animation_.to_json()}};
}

void Bowser::from_json(const json &j)
{
	position_.x = j["x"];
	position_.y = j["y"];
	velocity_.x = j["vx"];
	velocity_.y = j["vy"];
	hp_ = j["hp"];
	state_ = static_cast<Bowser_State>(j["state"]);
	score = j["score"];
	fire_cooldown_ = j["fire_cooldown"];
	jump_cooldown_ = j["jump_cooldown"];
	face_right_ = j["face_right"];
	dying_time_ = j["dying_time"];
	is_active = j["is_active"];
	is_dead = j["is_dead"];
	is_ground = j["is_ground"];
	first_appear = j["first_appear"];
	animation_.from_json(j["animation"]);
}
