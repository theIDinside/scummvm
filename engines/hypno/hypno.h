/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#ifndef HYPNO_H
#define HYPNO_H

#include "common/array.h"
#include "common/installshieldv3_archive.h"
#include "common/random.h"
#include "common/serializer.h"
#include "common/str-array.h"
#include "common/stream.h"
#include "engines/engine.h"
#include "graphics/font.h"
#include "graphics/fontman.h"
#include "graphics/managed_surface.h"

#include "hypno/grammar.h"
#include "hypno/libfile.h"

namespace Image {
class ImageDecoder;
}

namespace Graphics {
class ManagedSurface;
}

struct ADGameDescription;

namespace Hypno {

// debug channels
enum {
	kHypnoDebugMedia = 1 << 0,
	kHypnoDebugParser = 1 << 1,
	kHypnoDebugArcade = 1 << 2,
	kHypnoDebugScene = 1 << 3,
};

typedef Common::Array<Graphics::Surface *> Frames;

class HypnoEngine : public Engine {
private:
	Common::RandomSource *_rnd;
	Image::ImageDecoder *_image;

public:
	HypnoEngine(OSystem *syst, const ADGameDescription *gd);
	~HypnoEngine();

	const ADGameDescription *_gameDescription;
	bool isDemo() const;
	Common::Language _language;
	Common::Platform _platform;

	Audio::SoundHandle _soundHandle;
	Common::InstallShieldV3 _installerArchive;
	Common::List<LibFile*> _archive;

	Common::Error run() override;
	Levels _levels;
	Common::HashMap<Common::String, int> _sceneState;
	void resetSceneState();
	bool checkSceneCompleted();
	void runLevel(Common::String &name);
	void runScene(Scene &scene);
	void runArcade(ArcadeShooting &arc);

	void restartGame();
	void clearAreas();
	void initializePath(const Common::FSNode &gamePath) override;
	virtual void loadAssets();
	void parseScene(const Common::String &prefix, const Common::String &filename);
	void parseArcadeShooting(const Common::String &prefix, const Common::String &name, const Common::String &data);
	ShootSequence parseShootList(const Common::String &name, const Common::String &data);
	LibFile *loadLib(const Filename &prefix, const Filename &filename);

	// User input
	void clickedHotspot(Common::Point);
	bool hoverHotspot(Common::Point);

	// Cursors
	bool cursorPauseMovie(Common::Point);
	bool cursorExit(Common::Point);
	bool cursorMask(Common::Point);

	bool canLoadGameStateCurrently() override { return false; }
	bool canSaveAutosaveCurrently() override { return false; }
	bool canSaveGameStateCurrently() override { return false; }

	void syncGameStream(Common::Serializer &s);

	Common::String _prefixDir;
	Common::String convertPath(const Common::String &);
	void playVideo(MVideo &video);
	void skipVideo(MVideo &video);

	Graphics::Surface *decodeFrame(const Common::String &name, int frame, bool convert = true);
	Frames decodeFrames(const Common::String &name);
	void loadImage(const Common::String &file, int x, int y, bool transparent);
	void drawImage(Graphics::Surface &image, int x, int y, bool transparent);

	// Cursors
	Common::String _defaultCursor;
	void disableCursor();
	void defaultCursor();
	void changeCursor(const Common::String &cursor, uint32 n);
	void changeCursor(const Common::String &cursor);

	// Actions
	void runIntro(MVideo &video);
	void runMenu(Hotspots hs);
	void runBackground(Background *a);
	void runOverlay(Overlay *a);
	void runMice(Mice *a);
	void runEscape(Escape *a);
	void runQuit(Quit *a);
	void runCutscene(Cutscene *a);
	void runPlay(Play *a);
	void runAmbient(Ambient *a);
	void runWalN(WalN *a);
	void runGlobal(Global *a);
	void runTalk(Talk *a);
	void runChangeLevel(ChangeLevel *a);

	// Screen
	int _screenW, _screenH;
	Graphics::PixelFormat _pixelFormat;
	void changeScreenMode(const Common::String &mode);
	Graphics::ManagedSurface *_compositeSurface;
	uint32 _transparentColor;
	Common::Rect screenRect;
	void updateScreen(MVideo &video);
	void drawScreen();

	// intros
	Common::HashMap<Common::String, Videos> _intros;

	// levels
	Common::String _nextLevel;
	Common::String _currentLevel;
	uint32 _levelId;

	// hotspots
	Hotspots *_nextHotsToAdd;
	Hotspots *_nextHotsToRemove;
	HotspotsStack stack;

	// Movies
	Videos _nextSequentialVideoToPlay;
	Videos _nextParallelVideoToPlay;
	Videos _videosPlaying;

	// Sounds
	Filename _soundPath;
	Filename _music;
	void playSound(const Filename &filename, uint32);
	void stopSound();
	bool isSoundActive();
	bool _noStopSounds;

	// Arcade
	int detectTarget(const Common::Point &mousePos);
	virtual bool clickedPrimaryShoot(const Common::Point &mousePos);
	virtual bool clickedSecondaryShoot(const Common::Point &mousePos);
	virtual void drawShoot(const Common::Point &mousePos);
	virtual void shoot(const Common::Point &mousePos);
	virtual void hitPlayer();

	void drawCursorArcade(const Common::Point &mousePos);
	virtual void drawPlayer();
	virtual void drawHealth();
	int _health;
	int _maxHealth;
	int _score;
	Filename _shootSound;
	Shoots _shoots;
	Frames _playerFrames;
	int _playerFrameIdx;
	int _playerFrameSep;
	const Graphics::Font *_font;

	// Conversation
	Actions _conversation;
	bool _refreshConversation;
	virtual void showConversation();
	virtual void rightClickedConversation(const Common::Point &mousePos);
	virtual void leftClickedConversation(const Common::Point &mousePos);

	// Hardcoded puzzles
	virtual void runPuzzle(Puzzle puzzle);

	// Transitions
	void runTransition(Transition trans);

	// Credits
	virtual void showCredits();

	// Timers
	bool installTimer(uint32, Common::String *);
	void removeTimer();
};

class WetEngine : public HypnoEngine {
public:
	WetEngine(OSystem *syst, const ADGameDescription *gd);

	void loadAssets() override;
	void showCredits() override;
	bool clickedSecondaryShoot(const Common::Point &mousePos) override;
	void drawShoot(const Common::Point &target) override;
	void drawPlayer() override;
	void drawHealth() override;
};

class SpiderEngine : public HypnoEngine {
public:
	SpiderEngine(OSystem *syst, const ADGameDescription *gd);
	void loadAssets() override;
	void drawShoot(const Common::Point &target) override;
	void drawPlayer() override;
	void drawHealth() override;
	void runPuzzle(Puzzle puzzle) override;

	void showConversation() override;
	void rightClickedConversation(const Common::Point &mousePos) override;
	void leftClickedConversation(const Common::Point &mousePos) override;

private:
	void runMatrix(Puzzle puzzle);
};

class BoyzEngine : public HypnoEngine {
public:
	BoyzEngine(OSystem *syst, const ADGameDescription *gd);
	void loadAssets() override;
};

} // End of namespace Hypno

#endif
