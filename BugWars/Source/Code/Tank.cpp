#include "pch.h"
#include "Tank.h"
#include "Globals.h"
#include "Game.h"
#include "Bullet.h"
#include "Bug.h"

IMPLEMENT_RTTI(Tank);

Tank::Tank()
	
{
	disabled = false;
}

void Tank::OnUpdate(float dt)
{
}

BugBase* Tank::GetBugToShoot() const
{
	Bug* tar = nullptr;
	float min = std::numeric_limits<float>::max();
	for (auto obj : g_Game->objects) {
		if (auto bug = dynamic_cast<Bug*>(obj)) {
			if (bug->disabled || !bug->visible) {
				continue;
			}
			float dist2 = bug->position.Distance2(position);
			if (dist2 < min) {
				min = dist2;
				tar = bug;
			}
		}
	}
	return tar;
}

Point Tank::CalcShootDirection(Point target_pos, Point target_dir, float target_vel, float bullet_vel) const
{
	// a * sqr(x) + b * x + c == 0
	// a := sqr(target.velocityX) + sqr(target.velocityY) - sqr(projectile_speed)
	// b: = 2 * (target.velocityX * (target.startX - cannon.X)
	// + target.velocityY * (target.startY - cannon.Y))
	// c : = sqr(target.startX - cannon.X) + sqr(target.startY - cannon.Y)
	// next - square equation

	Point dPoint = target_pos - position;
	float a = std::powf(bullet_vel, 2) - std::powf(target_vel, 2);
	float b = dPoint.Dot(target_dir) * target_vel;
	float c = -dPoint.Dot(dPoint);

	float D = std::powf(b, 2) - a * c;
	float t2 = (b - sqrtf(D)) / a;
	float t1 = (b + sqrtf(D)) / a;
	if (t2 > t1 && t1 <= 0) {
		t1 = t2;
	}
	Point dir = (dPoint + target_dir * target_vel * t1) / (bullet_vel * t1);
	return dir;
}
