use std::env;

fn main() {
	let args: Vec<String> = env::args().collect();

	println!("a barbara eh {}", args[1]);
}

