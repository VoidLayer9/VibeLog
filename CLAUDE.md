# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

**VibeLog** is a minimalist blog engine built on the Cortex C sandbox template. It operates as a single-file application (`app.c`) that handles HTTP serving, JSON parsing, and file-based database management without external runtime dependencies beyond libc.

The project uses a sandboxed architecture where application logic stays in `app.c` and accesses all functionality through function pointers in the `appdeps` struct.

## Build & Run Commands

**Simple compile and run (most common):**
```bash
gcc main.c -o vibelog
./vibelog start --database-path ./database --root-password your_password
```

**Debug mode with hot-reload** (requires Darwin + CWebStudioFirmware):
```bash
darwin run_blueprint --target debug --compiler "gcc"
```

**Other build targets** (require Darwin, most require Docker/Podman):
```bash
darwin run_blueprint --target amalgamation          # Single-file release
darwin run_blueprint --target static_linux --provider docker
darwin run_blueprint --target windows --provider docker
darwin run_blueprint --target deb --provider docker
darwin run_blueprint --target rpm --provider docker
```

**VibeLog CLI Commands:**
- Start server: `./vibelog start --port 8080 --database-path ./database --root-password secret`
- Upload content: `./vibelog upload --path database/articles/new-post --url http://server:8080 --root-password secret`
- Download content: `./vibelog download --path database --url http://server:8080 --root-password secret`

Default server port is 8080 if not specified.

## Architecture

**Two-file model:**
- `main.c` — Server infrastructure, HTTP routing, and the `appdeps` function pointer table wiring. Bridges CWebStudio (HTTP server library) to the sandbox API. Not intended for direct editing by application developers.
- `app.c` — Application code sandbox. All VibeLog logic goes here. Uses no `#include` directives; instead accesses all functionality through the `appdeps` struct passed as function pointer table.

**Key types in `app.c`:**
- `appdeps` — Struct of function pointers providing: stdio, memory allocation, HTTP request/response, JSON (cJSON-based), file I/O, CLI argument parsing, and HTTP client
- `appstart` — Returned by `public_appstart()` to configure port, server handler, and custom props
- `public_appstart(appdeps *deps)` — Entry point called at startup; configure and return `appstart`
- The server handler function (e.g. `private_mainserver`) receives `appdeps *deps` and `void *props`

**VibeLog Database Structure:**
```
database/
├── categorys.json              # Global category definitions
├── articles/                   # Article content by date
│   └── YYYY/
│       └── MM/
│           └── DD/
│               └── <article_id>/
│                   ├── data.json       # Metadata (title, author, etc.)
│                   ├── content/en.html # Article body
│                   └── assets/thumbnail.jpg
├── authors/                    # Author profiles
│   └── <author_id>/
│       ├── data.json          # Profile info
│       └── assets/picture.jpg
├── metrics/                    # View analytics (auto-generated)
└── pages/                      # Static pages
```

**Dependencies** (header-only C libraries in `dependencies/`):
- **CWebStudio** (v5.3.0) — HTTP server
- **doTheWorld** (v11.2.0) — File I/O utilities  
- **CArgvParse** (v0.0.2) — CLI argument parsing
- **BearHttpsClient** (v0.9.2) — HTTPS client

**Build system:** Darwin (Lua-based), configured in `darwinconf.lua` with build recipes in `builds/`.

## Key Constraints

- `app.c` must never use `#include` — all functionality comes through the `appdeps` function pointer table
- When modifying `app.c`, always return the full file content including the type definitions and comments at the top  
- `main.c` wires the `appdeps` struct to actual library implementations; changes here affect the entire sandbox API surface
- VibeLog expects strict database folder structure — articles must be organized by date (YYYY/MM/DD)
- All JSON files must be valid and follow the expected schema (see README.md for examples)

## VibeLog-Specific Development Notes

- Articles are accessed via routes like `/article?date=YYYY/MM/DD&id=article_id`
- Categories can be toggled for navbar display via `categorys.json`
- Metrics are automatically tracked per article and category
- The CLI supports synchronization between local and remote instances
- Static assets are embedded at build time via `assets.c` and `assets.h`