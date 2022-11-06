# NERS 570: **Sp**arse **M**at**V**ec library

![Formatting](https://github.com/bkochuna/ners570f22-SpMV/actions/workflows/formatting-linting.yaml/badge.svg)
![Tests](https://github.com/bkochuna/ners570f22-SpMV/actions/workflows/tests.yml/badge.svg)

All PR's to this repo must pass formatting and linting checks before they can be merged.
To have these checks performed locally on your commits, run the following commands:

```bash
pre-commit install
```

This will install the pre-commit hooks into your local git repo.  Now, when you commit, the hooks will be run and any errors will be reported.
To manually run the checks, you can run:

```bash
pre-commit run --all-files
```
