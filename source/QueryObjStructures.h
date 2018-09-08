#include <string>
using namespace std;

typedef struct SELECT_VAR_CLAUSE {
	string variableType;
	string variableName;
} SELECT_VAR_CLAUSE;

// For Uses/Modifies relationship clauses
typedef struct STMT_PROC_VAR_RS_CLAUSE {
	string firstEntity;	// can be either a procedure name or a statement number 
	string variable;	// variable
	bool hasTransitiveClosure;
} STMT_PROC_VAR_RS_CLAUSE;

// For Follows/Parent relationship clauses
typedef struct STMT_RS_CLAUSE {
	int firstStmt;
	int secondStmt;
	bool hasTransitiveClosure;
} STMT_RS_CLAUSE;