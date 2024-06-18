use std::error::Error;

#[derive(Debug)]
pub enum TokenType{
    Expression,
    HexNumber,
    BinaryNumber,
    Integer,
    Float,
    Operator,
    FunctionDef,
    VariableDef,
    Identifier,
}

#[derive(Debug)]
pub struct Token{
    pub content: String,
    pub token_type: TokenType
}

#[derive(Debug)]
pub struct Lexer{
    pub tokens: Vec<Token>
}

impl Lexer{
    pub fn new(file: String) -> Result<Lexer, Box<dyn Error>>{
        let mut tokens: Vec<Token> = Vec::new();
        let mut content_bytes = file.as_bytes();

        for mut i in 0..file.len(){
            // skip whitespaces
            if content_bytes[i].is_ascii_whitespace() { continue; }

            // check for numbers
            if content_bytes[i].is_ascii_digit(){
                let mut number_vec: Vec<u8> = Vec::new();
                number_vec.push(content_bytes[i]);
                i += 1;
                loop{
                    if i == file.len() { break; }
                    if content_bytes[i].is_ascii_hexdigit() || content_bytes[i] as char == '.'
                        || content_bytes[i] as char == 'b' || content_bytes[i] as char == 'x'{
                        number_vec.push(content_bytes[i]);
                        i += 1;
                    } else {
                        if number_vec.len() == 1 {
                            tokens.push(Token{
                                content: String::from_utf8(number_vec.clone())?,
                                token_type: TokenType::Integer
                            });
                            break;
                        }
                        tokens.push(Token{
                            content: String::from_utf8(number_vec.clone())?,
                            token_type: if number_vec[0] as char == '0'{
                                match number_vec[1] as char {
                                    'x' => TokenType::HexNumber,
                                    'b' => TokenType::BinaryNumber,
                                    _ => {if number_vec.contains(&('.' as u8)){
                                        TokenType::Float
                                    } else {
                                        TokenType::Integer
                                    }}
                                }
                            } else {
                                if number_vec.contains(&('.' as u8)){
                                    TokenType::Float
                                } else {
                                    TokenType::Integer
                                }
                            }
                        });
                        break;
                    }
                }
                continue;
            }

            // TODO: other tokens
        }

        Ok(Lexer{ tokens })
    }
}