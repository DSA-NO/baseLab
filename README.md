# baseLab

This project is a small Geant4 application for testing geometry, materials, and particle generation in a simple setup.

## Quick start

If micromamba is missing or stale, refresh it first. These helper scripts are intended for Linux/macOS shells; on Windows, use WSL, Git Bash, or another Unix-like shell and follow the same steps.

```bash
cd baseLab
./scripts/install-micromamba.sh
export PATH="$HOME/.local/bin:$PATH"
```

Then use the shipped micromamba helper for the recommended workflow:

```bash
cd baseLab
./scripts/run-micromamba.sh build
./scripts/run-micromamba.sh run
```

This creates or reuses the `geant4-baseLab` environment from `environment.yml`, builds the app, and runs it in batch mode by default.

If you want an interactive shell inside the environment:

```bash
./scripts/run-micromamba.sh shell
```

You can also pass a macro directly:

```bash
./scripts/run-micromamba.sh run -b run.mac
```
