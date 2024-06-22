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

        let mut i : usize = 0;
        while i < content_bytes.len(){
            let mut token_vec: Vec<u8> = Vec::new();

            // skip whitespaces
            while content_bytes[i].is_ascii_whitespace() { i += 1; }

            // numbers
            if content_bytes[i].is_ascii_digit(){
                token_vec.push(content_bytes[i]); i += 1;
                while content_bytes[i].is_ascii_digit()
                    || content_bytes[i] as char == '.'
                    || content_bytes[i] as char == 'b'
                    || content_bytes[i] as char == 'x'{
                    token_vec.push(content_bytes[i]); i += 1;
                }

                // check if number is hex
                if token_vec[1] as char == 'x'{
                    if token_vec[0] as char == '0'{
                        for k in 2..token_vec.len(){
                            if !token_vec[k].is_ascii_hexdigit() {
                                return Err(Box::from("invalid hex number!"))
                            }
                        }
                    } else {
                        return Err(Box::from("invalid hex number!"))
                    }
                }
                // check if number is binary
                if token_vec[1] as char == 'b'{
                    if token_vec[0] as char == '0'{
                        for k in 2..token_vec.len(){
                            if !(token_vec[k] as char == '0' || token_vec[k] as char == '1'){
                                return Err(Box::from("invalid binary number!"))
                            }
                        }
                    } else {
                        return Err(Box::from("invalid binary number!"))
                    }
                }

                // check if number is valid
                let mut non_digit_amount : u16 = 0;
            }
        }

        Ok(Lexer{ tokens })
    }
}