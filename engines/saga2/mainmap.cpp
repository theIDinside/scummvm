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
 * aint32 with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 *
 * Based on the original sources
 *   Faery Tale II -- The Halls of the Dead
 *   (c) 1993-1996 The Wyrmkeep Entertainment Co.
 */


#define FORBIDDEN_SYMBOL_ALLOW_ALL // FIXME: Remove

#include "saga2/std.h"
#include "saga2/fta.h"
#include "saga2/mainmap.h"

namespace Saga2 {

void parseCommandLine(int argc, char *argv[]) {
	warning("STUB: parseCommandLine()");
}

uint32 pickHeapSize(uint32 minHeap) {
	warning("STUB: pickHeapSize()");
	return 0;
}

void initCleanup() {
	warning("STUB: initCleanup()");
}
bool initErrorHandlers() {
	warning("STUB: initErrorHandlers()");
	return false;
}
void cleanupErrorHandlers() {
	warning("STUB: cleanupErrorHandlers()");
}

bool initializeGame() {
	if (setupGame())
		return TRUE;

	return FALSE;
}
void shutdownGame() {
	warning("STUB: shutdownGame");
}

bool initSystemTimer() {
	warning("STUB: initSystemTimer()");
	return true;
}
void cleanupSystemTimer() {
	warning("STUB: cleanupSystemTimer()");
}

void cleanupSystemTasks() {
	warning("STUB: cleanupSystemTasks()");
}
void cleanupPaletteData() {
	warning("STUB: cleanupPaletteData()");
}

void mousePoll() {
	warning("STUB: mousePoll()");
}

bool handlingMessages() {
	warning("STUB: handlingMessages()");
	return false;
}

void displayEventLoop() {
	warning("STUB: displayEventLoop()");
}

void initBreakHandler() {
	warning("STUB: initBreakHandler()");
}

void cleanupBreakHandler() {
	warning("STUB: cleanupBreakHandler()");
}

void breakEventLoop() {
	warning("STUB: breakEventLoop()");
}

} // end of namespace Saga2