#pragma once

#pragma once
#include <string>
#include <vector>

namespace keywords {
	const std::string PROCEDURE = "procedure";
	const std::string ASSIGNMENT = "=";

	namespace query {
		const std::string SELECT_VAR = "select";
		const std::string ASSIGNMENT_VAR = "assign";
		const std::string VARIABLE_VAR = "variable";
		const std::string STMT_VAR = "stmt";
		const std::string PROC_VAR = "procedure";
		const std::string WHILE_VAR = "while";
		const std::vector<string> DESIGN_ENTITY = { ASSIGNMENT_VAR, VARIABLE_VAR, STMT_VAR, PROC_VAR, WHILE_VAR };
	}
	
	namespace clauseParamType {
		const std::string SYNONYM = "syn";
		const std::string STMT_NO = "stmtNo";
		const std::string PROC_NAME = "procName";
		const std::string VARIABLE = "variable";
		const std::string UNDERSCORE = "underscore";
	}
};
