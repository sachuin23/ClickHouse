#pragma once

#include <Parsers/IParserBase.h>


namespace DB
{


/** Cases:
  *
  * Normal case:
  * INSERT INTO [db.]table (c1, c2, c3) VALUES (v11, v12, v13), (v21, v22, v23), ...
  * INSERT INTO [db.]table VALUES (v11, v12, v13), (v21, v22, v23), ...
  *
  * Insert of data in an arbitrary format.
  * The data itself comes after LF(line feed), if it exists, or after all the whitespace characters, otherwise.
  * INSERT INTO [db.]table (c1, c2, c3) FORMAT format \n ...
  * INSERT INTO [db.]table FORMAT format \n ...
  *
  * Insert the result of the SELECT query.
  * INSERT INTO [db.]table (c1, c2, c3) SELECT ...
  * INSERT INTO [db.]table SELECT ...
  */
class ParserInsertQuery : public IParserBase
{
protected:
    const char * getName() const { return "INSERT query"; }
    bool parseImpl(Pos & pos, Pos end, ASTPtr & node, Pos & max_parsed_pos, Expected & expected);
};

}
