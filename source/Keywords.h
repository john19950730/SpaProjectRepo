#pragma once

#pragma once
#include <string>
#include <vector>

namespace keywords {
	const std::string PROCEDURE = "procedure";
	const std::string ASSIGNMENT = "=";

	namespace query {
		const std::string VARIABLE_VAR = "variable";
		const std::string PROC_VAR = "procedure";
		const std::string STMT_VAR = "stmt";
		const std::string ASSIGNMENT_VAR = "assign";
		const std::string IF_VAR = "if";
		const std::string WHILE_VAR = "while";
		const std::string READ_VAR = "read";
		const std::string PRINT_VAR = "print";
		const std::string CALL_VAR = "call";
		const std::vector<string> STATEMENTS = { STMT_VAR, ASSIGNMENT_VAR, IF_VAR, WHILE_VAR, READ_VAR, PRINT_VAR, CALL_VAR };
		const std::vector<string> PATTERN_TYPES = { ASSIGNMENT_VAR, IF_VAR, WHILE_VAR };

		const std::string USES_RS = "uses";
		const std::string MODIFIES_RS = "modifies";
		const std::string FOLLOWS_RS = "follows";
		const std::string PARENT_RS = "parent";
	}
	
	namespace clauseParamType {
		const std::string SYNONYM = "syn";
		const std::string STMT_NO = "stmtNo";
		const std::string PROC_NAME = "procName";
		const std::string VARIABLE = "variable";
		const std::string UNDERSCORE = "underscore";
	}
};
