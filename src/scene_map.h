/*
 * This file is part of EasyRPG Player.
 *
 * EasyRPG Player is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * EasyRPG Player is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with EasyRPG Player. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef EP_SCENE_MAP_H
#define EP_SCENE_MAP_H

// Headers
#include "scene.h"
#include "spriteset_map.h"
#include "window_message.h"
#include "window_varlist.h"
#include "game_map.h"

/**
 * Scene Map class.
 */
class Scene_Map: public Scene {
public:
	/**
	 * Constructor.
	 */
	Scene_Map(bool from_save = false);

	~Scene_Map();

	void Start() override;
	void Continue(SceneType prev_scene) override;
	void Update() override;
	void TransitionIn(SceneType prev_scene) override;
	void TransitionOut(SceneType next_scene) override;
	void DrawBackground() override;

	void CallBattle();
	void CallShop();
	void CallName();
	void CallMenu();
	void CallSave();
	void CallLoad();
	void CallDebug();
	void CallGameover();

	std::unique_ptr<Spriteset_Map> spriteset;

private:
	enum TeleportTransitionRule {
		eTransitionNormal,
		eTransitionFade,
		eTransitionForceFade,
		eTransitionNone
	};

	void Start2(MapUpdateAsyncContext actx);

	void StartPendingTeleport(bool use_default_transition, bool no_erase);
	void FinishPendingTeleport(bool use_default_transition, bool defer_recursive_teleports);
	void FinishPendingTeleport2(MapUpdateAsyncContext actx, bool use_default_transition, bool defer_recursive_teleports);

	void PreUpdate(MapUpdateAsyncContext& actx);

	// Calls map update
	void UpdateStage1(MapUpdateAsyncContext actx);
	// Handles pending teleport and scene changes.
	void UpdateStage2();

	void UpdateSceneCalling();

	template <typename F> void AsyncNext(F&& f);
	template <typename F> void OnAsyncSuspend(F&& f, bool is_preupdate);

	std::unique_ptr<Window_Message> message_window;

	int debug_menuoverwrite_counter = 0;
	bool from_save;
	bool screen_erased_by_event = false;
};

#endif
