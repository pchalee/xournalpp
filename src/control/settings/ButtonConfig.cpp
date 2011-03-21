#include "ButtonConfig.h"
#include "../ToolHandler.h"

ButtonConfig::ButtonConfig(ToolType action, int color, ToolSize size, DrawingType drawingType, EraserType eraserMode) {
	this->action = action;
	this->color = color;
	this->size = size;
	this->drawingType = drawingType;
	this->eraserMode = eraserMode;
	this->disableDrawing = false;
}

bool ButtonConfig::getDisableDrawing() {
	return this->disableDrawing;
}

ToolType ButtonConfig::getAction() {
	return this->action;
}

void ButtonConfig::acceptActions(ToolHandler * toolHandler) {
	if (this->action != TOOL_NONE) {
		toolHandler->selectTool(this->action);

		if (this->action == TOOL_PEN || this->action == TOOL_HILIGHTER) {

			if (this->drawingType == DRAWING_TYPE_DONT_CHANGE) {
				// nothing to do
			} else if (this->drawingType == DRAWING_TYPE_STROKE_RECOGNIZER) {
				toolHandler->setRuler(false);
				toolHandler->setShapeRecognizer(true);
			} else if (this->drawingType == DRAWING_TYPE_RULER) {
				toolHandler->setRuler(true);
				toolHandler->setShapeRecognizer(false);
			} else if (this->drawingType == DRAWING_TYPE_NONE) {
				toolHandler->setRuler(false);
				toolHandler->setShapeRecognizer(false);
			}

			if (this->size != TOOL_SIZE_NONE) {
				toolHandler->setSize(this->size);
			}
		}

		if (this->action == TOOL_PEN || this->action == TOOL_HILIGHTER || this->action == TOOL_TEXT) {
			toolHandler->setColor(this->color);
		}

		if (this->action == TOOL_ERASER && this->eraserMode != ERASER_TYPE_NONE) {
			toolHandler->setEraserType(this->eraserMode);
		}
	}
}