#![recursion_limit = "131"]
use burn::{
    backend::{ndarray::NdArrayDevice, Autodiff, NdArray},
    data::dataset::Dataset,
    optim::AdamConfig,
};
use harmonics_generator::{
    inference,
    model::ModelConfig,
    training::{self, TrainingConfig},
};

fn main() {
    type MyBackend = NdArray;
    type MyAutodiffBackend = Autodiff<MyBackend>;

    let device = NdArrayDevice::Cpu;

    // All the training artifacts will be saved in this directory
    let artifact_dir = "/tmp/guide";

    // Train the model
    training::train::<MyAutodiffBackend>(
        artifact_dir,
        TrainingConfig::new(ModelConfig::new(10, 512), AdamConfig::new()),
        device.clone(),
    );

    // Infer the model
    inference::infer::<MyBackend>(
        artifact_dir,
        device,
        burn::data::dataset::vision::MnistDataset::test()
            .get(42)
            .unwrap(),
    );
}
