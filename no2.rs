use std::io;
fn main() {
    let (rows, cols) = get_matrix_size();
    println!("Enter the elements for the first matrix:");
    let matrix1 = get_matrix(rows, cols);
    println!("Enter the elements for the second matrix:");
    let matrix2 = get_matrix(rows, cols);
    let result = add_matrices(&matrix1, &matrix2, rows, cols);
    println!("The result of the addition is:");
    print_matrix(&result, rows, cols);}
fn get_matrix_size() -> (usize, usize) {
    let mut input = String::new();
    println!("Enter the number of rows and columns (separated by space):");
    io::stdin().read_line(&mut input).unwrap();
    let parts: Vec<usize> = input
        .trim()
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect();
    (parts[0], parts[1])}
fn get_matrix(rows: usize, cols: usize) -> Vec<Vec<i32>> {
    let mut matrix = Vec::new();
    for i in 0..rows {
        println!("Enter the elements for row {} (separated by space):", i + 1);
        let mut input = String::new();
        io::stdin().read_line(&mut input).unwrap();
        let row: Vec<i32> = input
            .trim()
            .split_whitespace()
            .map(|x| x.parse().unwrap())
            .collect();
        if row.len() != cols {
            panic!("Each row must have exactly {} elements.", cols);}
        matrix.push(row);}matrix}
fn add_matrices(
    matrix1: &Vec<Vec<i32>>,
    matrix2: &Vec<Vec<i32>>,
    rows: usize,
    cols: usize,
) -> Vec<Vec<i32>> {
    let mut result = Vec::with_capacity(rows);
    for i in 0..rows {
        let mut row = Vec::with_capacity(cols);
        for j in 0..cols {
            row.push(matrix1[i][j] + matrix2[i][j]);}
        result.push(row);}
    result}

fn print_matrix(matrix: &Vec<Vec<i32>>, rows: usize, cols: usize) {
    for i in 0..rows {
        for j in 0..cols {
            print!("{} ", matrix[i][j]);}
        println!(); }}
