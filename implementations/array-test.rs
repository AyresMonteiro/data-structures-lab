use std::io;

fn get_i32_from_stdin() -> Vec<i32> {
	let mut line = String::new();

	io::stdin()
		.read_line(&mut line)
		.expect("Error while reading from stdin");
	
	let numbers = line.split_whitespace()
		.map(|num| num.parse::<i32>().expect("Error while parsing string to i32"))
		.collect::<Vec<i32>>();

	numbers
}

fn pop_off (vector: &mut Vec<i32>, start_index: usize) {
	while vector.len() > start_index {
		vector.pop();
	}
}

fn collect_numbers_from_stdin () -> Vec<i32> {
	let mut vector: Vec<i32> = Vec::new();

	let mut can_run = true;

	while can_run {
		let mut numbers = get_i32_from_stdin();

		can_run = numbers.iter().find(|&&num| num == -1).is_none();

		if ! can_run {
			let end_position: usize = numbers.iter().position(|&num| num == -1).unwrap();
			pop_off(&mut numbers, end_position);
		}

		vector.append(&mut numbers);
	}

	vector
}

fn main () {
	let first_vector = collect_numbers_from_stdin();
	let second_vector = collect_numbers_from_stdin();

	println!("1: {:?}", first_vector);
	println!("2: {:?}", second_vector);
}

