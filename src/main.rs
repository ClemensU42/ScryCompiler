mod lexer;

use std::error::Error;
use std::fs;

fn main() -> Result<(), Box<dyn Error>>{
    let mut input_file: String = String::new();
    for i in 0..std::env::args().len(){
        match std::env::args().nth(i).unwrap().as_str(){
            "-i" => {input_file = std::env::args().nth(i + 1).unwrap()}
            _ => {}
        }
    }

    if input_file.is_empty() { return Err(Box::from("no input file specified!")); }
    let input_file_content: String = fs::read_to_string(input_file)?;
    println!("{input_file_content}");
    Ok(())
}
