# baseLab

This project is a small Geant4 application for testing geometry, materials, and particle generation in a simple setup.

## Quick start

Use the shipped micromamba helper for the recommended workflow:

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
