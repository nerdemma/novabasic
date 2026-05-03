#include "../lib/common.h"
#include "../lib/parser.h"
static const char *expr_ptr;

// recursive internals
double parse_comparison();
double parse_expression();
double parse_term();
double parse_factor();


double evaluate(const char *s) {
	
    if (!s) return 0;
    while (isspace(*s)) s++;
    if(*s == '\0') return 0;
    expr_ptr = s;
    return parse_comparison(); 
}


double parse_comparison() {
    double x = parse_expression();
    while (1) {
        while (isspace(*expr_ptr)) expr_ptr++;
        
        if (strncmp(expr_ptr, "==", 2) == 0) {
            expr_ptr += 2;
            x = (x == parse_expression());
        } else if (strncmp(expr_ptr, "<>", 2) == 0) {
            expr_ptr += 2;
            x = (x != parse_expression());
        } else if (strncmp(expr_ptr, "<=", 2) == 0) {
            expr_ptr += 2;
            x = (x <= parse_expression());
        } else if (strncmp(expr_ptr, ">=", 2) == 0) {
            expr_ptr += 2;
            x = (x >= parse_expression());
        } else if (*expr_ptr == '<') {
            expr_ptr++;
            x = (x < parse_expression());
        } else if (*expr_ptr == '>') {
            expr_ptr++;
            x = (x > parse_expression());
        } else {
            return x;
        }
    }
}


double parse_expression()
{
	double x = parse_term();
	while(1)
	{
	while(isspace(*expr_ptr)) expr_ptr++;
	if(*expr_ptr == '+'){ expr_ptr++; x+= parse_term();}
	else if(*expr_ptr == '-'){ expr_ptr++; x -= parse_term();}
	else return x;
	}
}


double parse_term()
{
double x = parse_factor();
	while(1)
	{
		while(isspace(*expr_ptr)) expr_ptr++;
		if(*expr_ptr == '*'){ expr_ptr++; x *= parse_factor(); }
		else if(*expr_ptr == '/'){ 
		expr_ptr++; 
		double d = parse_factor();
		x = (d!=0) ? x / d : 0;
		} else return x;
	}
}

double parse_factor()
{
while(isspace(*expr_ptr)) expr_ptr++;

	if(isdigit(*expr_ptr) || *expr_ptr == '.'){
	char *end;
	double x = strtod(expr_ptr, &end);
	expr_ptr = end;
	return x;
	}

	if(isalpha(*expr_ptr))
	{
	int index = toupper(*expr_ptr) - 'A';
	expr_ptr++;
	return (index >=0 && index < 26)? variables[index]:0;
	}


	if (*expr_ptr == '(' ){
	expr_ptr++;
	double x = parse_expression();
	if (*expr_ptr == ')') expr_ptr++;
	return x;
	}

return 0;
}
