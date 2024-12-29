{ pkgs ? import <nixpkgs> {} }:
pkgs.mkShell {
	buildInputs = with pkgs; [
		xorg.libX11
		xorg.libXinerama
		xorg.libXi
		xorg.libXcursor
		xorg.libXrandr
		libxkbcommon
		wayland
		wayland-scanner
	];
}

