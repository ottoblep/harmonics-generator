#![recursion_limit = "131"]
use burn::{backend::{NdArray}, data::dataset::Dataset};
use harmonics_generator::inference;

fn main() {
    type MyBackend = NdArray;

    let device = burn::backend::ndarray::NdArrayDevice::Cpu;

    // All the training artifacts are saved in this directory
    let artifact_dir = "/tmp/guide";

    // Infer the model
    inference::infer::<MyBackend>(
        artifact_dir,
        device,
        burn::data::dataset::vision::MnistDataset::test()
            .get(42)
            .unwrap(),
    );
}
