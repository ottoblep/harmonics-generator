#![recursion_limit = "131"]
use burn::{backend::Wgpu, data::dataset::Dataset};
use harmonics_generator::inference;

fn main() {
    type MyBackend = Wgpu<f32, i32>;

    let device = burn::backend::wgpu::WgpuDevice::default();

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
