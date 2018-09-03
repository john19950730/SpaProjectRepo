class TNode
{
protected:
	string type;
	string value;
public:
	TNode() : type(""), value("") {}
	TNode(string type, string value) : type(type), value(value) {}
	TNode *parent;
	TNode *left;
	TNode *right;
};