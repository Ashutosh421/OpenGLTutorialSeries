#pragma once

struct IKeyEvent {
	virtual void OnKeyDown();
	virtual void OnKeyPressed();
	virtual void OnKeyUp();
};