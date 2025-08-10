use burn::backend::NdArray;
use harmonics_generator::model::ModelConfig;

fn main() {
    type MyBackend = NdArray;

    let device = Default::default(); 
    let model = ModelConfig::new(10, 512).init::<MyBackend>(&device);

    println!("{model}");
}
