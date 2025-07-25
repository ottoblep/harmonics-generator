{
  description = "harmonics_generator";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-24.11";
    systems.url = "github:nix-systems/default";
  };

  outputs = {
    self,
    nixpkgs,
    systems,
    ...
  }: let
    forEachSystem = nixpkgs.lib.genAttrs (import systems);
    pkgsFor = forEachSystem (system: import nixpkgs {inherit system;});
  in {
    formatter = forEachSystem (system: pkgsFor.${system}.alejandra);

    devShells = forEachSystem (system: {
      default = pkgsFor.${system}.mkShell {
        packages = with pkgsFor.${system}; [
          libllvm
          cmake
          gtest
        ];
      };
    });

    packages = forEachSystem (system: {
      default = pkgsFor.${system}.stdenv.mkDerivation {
        pname = "harmonics_generator";
        version = "0.1.0";
        src = ./.;

        nativeBuildInputs = with pkgsFor.${system}; [
          cmake
        ];
        buildInputs = with pkgsFor.${system}; [
          gtest
        ];
      };
    });

    apps = forEachSystem (system: {
      default = {
        type = "app";
        program = "${self.packages.${system}.default}/bin/harmonics_generator";
      };
    });
  };
}
