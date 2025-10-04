/*

How to use?
***********

If you have Nix installed, you can get an environment with everything
needed to compile nautilus-python by running:

    $ nix-shell

at the root of the nautilus-python repository.

You can also compile nautilus-python and ‘install’ it by running:

    $ nix-build

at the root of the nautilus-python repository. The command will install
nautilus-python to a location under Nix store and create a ‘result’ symlink
in the current directory pointing to the in-store location.

The dependencies are pinned, you can update them to latest versions with:

    $ nix-shell --run 'npins update'

How to tweak default arguments?
*******************************

Nix supports the ‘--arg’ option (see nix-build(1)) that allows you
to override the top-level arguments.

For instance, to use your local copy of Nixpkgs:

    $ nix-build --arg pkgs "import $HOME/Projects/nixpkgs {}"

Or to speed up the build by not running the test suite:

    $ nix-build --arg doCheck false

*/

{
  # Nixpkgs instance, will default to one from npins.
  pkgs ? null,
  # Whether to run tests when building File Roller using nix-build.
  doCheck ? true,
  # Whether to build File Roller, or shell for developing it.
  # We do not use lib.inNixShell because that would also apply
  # when in a nix-shell of some package depending on this one.
  shell ? false,
} @ args:

let
  # Pinned Nix dependencies (e.g. Nixpkgs) managed by npins.
  sources = import ./npins/default.nix;

  # Setting pkgs to the pinned version
  # when not overridden in args.
  pkgs =
    if args.pkgs or null == null
    then
      import sources.nixpkgs {
        overlays = [];
        config = {};
      }
    else args.pkgs;

  inherit (pkgs) lib;

  # Function for building File Roller or shell for developing it.
  makeDerivation =
    if shell
    then pkgs.mkShell
    else pkgs.stdenv.mkDerivation;
in
makeDerivation rec {
  name = "nautilus-python";

  outputs = [ "out" "devdoc" ];

  src =
    let
      # Do not copy to the store paths listed in .gitignore files
      cleanSource = path: pkgs.nix-gitignore.gitignoreFilterRecursiveSource (_: _: true) [ ] path;
    in
    if shell then null else cleanSource ./.;

  # Dependencies for build platform
  nativeBuildInputs = with pkgs; ([
    pkg-config
    meson
    ninja
    gtk-doc
    docbook-xsl-nons
    docbook_xml_dtd_412
  ] ++ lib.optionals shell [
    npins
  ]);

  # Dependencies for host platform
  buildInputs = with pkgs; [
    python3
    python3.pkgs.pygobject3
    nautilus
  ];

  inherit doCheck;
}
