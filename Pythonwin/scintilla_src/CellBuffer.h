// Scintilla source code edit control
// CellBuffer.h - manages the text of the document
// Copyright 1998-1999 by Neil Hodgson <neilh@scintilla.org>
// The License.txt file describes the conditions under which this software may be distributed.

#ifndef CELLBUFFER_H
#define CELLBUFFER_H

// This holds the marker identifier and the marker type to display.
// MarkerHandleNumbers are members of lists.
struct MarkerHandleNumber {
	int handle;
	int number;
	MarkerHandleNumber *next;
};

// A marker handle set contains any number of MarkerHandleNumbers
class MarkerHandleSet {
	MarkerHandleNumber *root;
public:
	MarkerHandleSet();
	~MarkerHandleSet();
	int Length();
	int NumberFromHandle(int handle);
	int MarkValue();	// Bit set of marker numbers
	bool Contains(int handle);
	bool InsertHandle(int handle, int markerNum);
	void RemoveHandle(int handle);
	void RemoveNumber(int markerNum);
	void CombineWith(MarkerHandleSet *other);
};

// Each line stores the starting position of the first character of the line in the cell buffer
// and potentially a marker handle set. Often a line will not have any attached markers.
struct LineData {
	int startPosition;
	MarkerHandleSet *handleSet;
	LineData() : startPosition(0), handleSet(0) {
	}
};

// The line vector contains information about each of the lines in a cell buffer.
class LineVector {
public:
	enum { growSize = 4000 };
	int lines;
	LineData *linesData;
	int size;
	
	// Handles are allocated sequentially and should never have to be reused as 32 bit ints are very big.
	int handleCurrent;
	
	LineVector();
	~LineVector();
	void Init();

	void Expand(int sizeNew);
	void InsertValue(int pos, int value);
	void SetValue(int pos, int value);
	void Remove(int pos);
	int LineFromPosition(int pos);
	
	int AddMark(int line, int marker);
	void MergeMarkers(int pos);
	void DeleteMark(int line, int markerNum);
	void DeleteMarkFromHandle(int markerHandle);
	int LineFromHandle(int markerHandle);
};

// Actions are used to store all the information required to perform one undo/redo step.
enum actionType { insertAction, removeAction, startAction };
class Action {
public:
	actionType at;
	int position;
	char *data;
	int lenData;

	Action();
	~Action();
	void Create(actionType at_, int position_=0, char *data_=0, int lenData_=0);
	void Destroy();
	void Grab(Action *source);
};

enum undoCollectionType { undoCollectNone, undoCollectAutoStart, undoCollectManualStart };

// Holder for an expandable array of characters that supports undo and line markers
// Based on article "Data Structures in a Bit-Mapped Text Editor"
// by Wilfred J. Hansen, Byte January 1987, page 183
class CellBuffer {
private:
	char *body;
	int size;
	int length;
	int part1len;
	int gaplen;
	char *part2body;
	bool readOnly;

	Action *actions;
	int lenActions;
	int maxAction;
	int currentAction;
	undoCollectionType collectingUndo;
	int undoSequenceDepth;
	int savePoint;

	LineVector lv;
	
	void GapTo(int position);
	void RoomFor(int insertionLength);

	void EnsureUndoRoom();
	void AppendAction(actionType at, int position, char *data, int length);

	inline char ByteAt(int position);
	void SetByteAt(int position, char ch);

public:

	CellBuffer(int initialLength = 4000);
	~CellBuffer();
	
	// Retrieving positions outside the range of the buffer works and returns 0
	char CharAt(int position);
	void GetCharRange(char *buffer, int position, int lengthRetrieve);
	char StyleAt(int position);
	
	int ByteLength();
	int Length();
	int Lines();
	int LineStart(int line);
	int LineFromPosition(int pos) { return lv.LineFromPosition(pos); }
	void InsertString(int position, char *s, int insertLength);
	void InsertCharStyle(int position, char ch, char style);
	
	// Setting styles for positions outside the range of the buffer is safe and has no effect.
	// True is returned if the style of a character changed.
	bool SetStyleAt(int position, char style, char mask=0xff);
	bool SetStyleFor(int position, int length, char style, char mask);
	
	void DeleteChars(int position, int deleteLength);

	bool IsReadOnly();
	void SetReadOnly(bool set);

	// The save point is a marker in the undo stack where the container has stated that 
	// the buffer was saved. Undo and redo can move over the save point.
	void SetSavePoint();
	bool IsSavePoint();

	// Line marker functions
	int AddMark(int line, int markerNum);
	void DeleteMark(int line, int markerNum);
	void DeleteMarkFromHandle(int markerHandle);
	int GetMark(int line);
	void DeleteAllMarks(int markerNum);
	int LineFromHandle(int markerHandle);
 
	// Without undo
	void BasicInsertString(int position, char *s, int insertLength);
	void BasicDeleteChars(int position, int deleteLength);

	undoCollectionType SetUndoCollection(undoCollectionType collectUndo);
	bool IsCollectingUndo();
	void AppendUndoStartAction();
	void BeginUndoAction();
	void EndUndoAction();
	void DeleteUndoHistory();
	int Undo(int *posEarliestChanged=0);
	int Redo(int *posEarliestChanged=0);
	bool CanUndo();
	bool CanRedo();
};

#define CELL_SIZE	2

#endif
