
class functionVisitor : public ifccBaseVisitor
{
private:
    /* data */
public:
    functionVisitor(/* args */) {}
    ~functionVisitor() {}

    virtual antlrcpp::Any visitFunction(ifccParser::FunctionContext *ctx) override;
};


