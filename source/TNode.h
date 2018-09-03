class TNode
{
protected:
	string type;
	string value;
public:
	TNode(string type, string value) : type(type), value(value) {}
	TNode *left;
	TNode *right;
};