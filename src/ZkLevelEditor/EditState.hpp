#pragma once

namespace Zk {
namespace LevelEditor {

enum class EditState : int
{
	IDLE = 0,
	MAKE_TRIANGLE_SELECTED_1 = 1,
	MAKE_TRIANGLE_SELECTED_2 = 2,
	TRIANGLE_PAINTING = 3
};

}}
