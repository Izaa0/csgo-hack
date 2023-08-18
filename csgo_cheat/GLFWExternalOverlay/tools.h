#pragma once
#include <cstdint>
#include <cstddef>
#include "datatypes.h"



struct Player
{
	uintptr_t local_player;
	uintptr_t team_id;
	ViewMatrix matrix;
}plr;

struct Game
{
	uintptr_t module_base;
	uintptr_t entity_list;
	
}game;

struct Entity
{
	uintptr_t entity_base;
	uintptr_t entity_list;

	uintptr_t armor;
	uintptr_t health;

	uintptr_t life_state;
	uintptr_t team_id;

	Vec3 vec_origin;
	Vec3 head_origin;

	Vec2 head_coords;
	Vec2 feet_coords;

	uintptr_t dormant;

}entity;

void DrawBox(Vec2& feetCoords, Vec2& headCoords);

void DrawSnapLines(Vec2& feetCoords);

void DrawHealthBar(Vec2& feetCoords, Vec2& headCoords, int health);

void DrawArmorBar(Vec2& feetCoords, Vec2& headCoords, int armor);