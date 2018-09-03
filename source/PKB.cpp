#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "PKB.h"
#include "TNode.h"

static int varTableIndex = 0;
static int varTableCapacity = 100;
static string varTable[100];

static int lineNumber;

static TNode* root;
static TNode* nextProc;
static TNode* nextStmt;

int PKB::setProcToAST(PROC p, TNode* r) {
	return NULL;
}

TNode* PKB::getRootAST (PROC p){
	return NULL;
}

int PKB::addVariable(string varName)
{
	*(varTable + varTableIndex) = varName;
	return ++varTableIndex;
}

void PKB::newProgram(string progName)
{
	root = &TNode("program", progName);
	nextProc = root->left = &TNode("procList", "");
	root->left->parent = root;
}

void PKB::newProcedure(string procName)
{
	TNode* proc = &TNode("procedure", procName);
	nextProc->left = proc;
	proc->parent = nextProc;
	nextProc = nextProc->right = &TNode("", "");

	nextStmt = proc->left = &TNode("stmtList", "");
}

void PKB::addAssignment(string variableName, int immediate)
{
	TNode* stmt = &TNode("assignment", ++lineNumber + "");
	stmt->left = &TNode("variable", variableName);
	stmt->right = &TNode("expression", immediate + "");

	nextStmt->left = stmt;
	nextStmt = nextStmt->right = &TNode("", "");
}

bool PKB::setModifies(int stmtNo, string varName)
{
	return false;
}

bool PKB::isFollows(int stmtNo1, int stmtNo2)
{
	return false;
}

bool PKB::isModifies(int stmtNo1, string varName)
{
	return false;
}

int * PKB::getAssignmentStmts()
{
	static int dummy[] { 0 } ;
	return dummy;
}
