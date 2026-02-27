# VibeLog

**VibeLog** is a minimalist, industrial-aesthetic blog engine built on the [Cortex](https://github.com/VoidLayer9/Cortex) C sandbox template. It operates as a single-file application (`app.c`) that handles everything from HTTP serving to JSON parsing and database management, without external runtime dependencies beyond libc.

Designed for "vibecoding" — programming with intent and aesthetic precision — VibeLog features a dark, brutalist interface inspired by high-performance terminals and dashboards.

## Features

- **Single-File Architecture**: All logic resides in `app.c`.
- **JSON File-Based Database**: No SQL required; data is stored in structured JSON files.
- **Built-in HTTP Server**: Custom router handling articles, authors, and static assets.
- **CLI Management**: Tools for synchronization (upload/download) and server control.
- **Dynamic Metrics**: Tracks views per article and category in real-time.
- **Markdown/HTML Content**: Articles support rich HTML content.

---

## Installation & Setup

### Pre-compiled Binaries (Recommended)

Download the latest pre-compiled version for your platform from the [Releases page](https://github.com/VoidLayer9/VibeLog/releases/tag/0.0.5).

### Build from Source

1. **Clone the Repository**
   ```bash
   git clone https://github.com/your-username/vibelog.git
   cd vibelog
   ```

2. **Compile**
   Use standard GCC or Clang:
   ```bash
   gcc main.c -o vibelog
   ```

   **Advanced Builds:**
   
   Ensure you have [Darwin](https://github.com/OUIsolutions/Darwin) installed. For cross-compilation targets, [Docker](https://docs.docker.com/get-docker/) or [Podman](https://podman.io/getting-started/installation) is required.

   *   **Static Linux Binary** (Runs on any distro):
       ```bash
       darwin run_blueprint --target static_linux --provider docker
       ```

   *   **Windows Executable** (.exe):
       ```bash
       darwin run_blueprint --target windows --provider docker
       ```

   *   **Debian Package** (.deb):
       ```bash
       darwin run_blueprint --target deb --provider docker
       ```

   *   **RPM Package** (.rpm):
       ```bash
       darwin run_blueprint --target rpm --provider docker
       ```

   *   **Debug Mode** (Hot Reload):
       ```bash
       darwin run_blueprint --target debug --compiler "gcc"
       ```

3. **Initialize Database**
   The application expects a `database/` directory structure. See [Database Structure](#database-structure) below or refer to `prompts/1.database_creation.md` for a complete setup guide.

---

## Usage

VibeLog includes a CLI for starting the server and managing content synchronization.

### 1. Start the Server
Run the blog locally or in production:

```bash
./vibelog start --port 8080 --root-password secret_pass [--database-path ./database]
```

*   `--port`: Port to listen on (default: 8080).
*   `--root-password`: Admin password for API operations (required).
*   `--database-path`: Path to the database folder (optional, default: `./database`).
*   `--markdown-converter-command`: Command template for converting Markdown to HTML (optional). See [Markdown Support](#markdown-support) below.

### Markdown Support

VibeLog supports Markdown articles via an external converter command. When configured, article content can be written in `content.md` instead of `content.html`. VibeLog will convert the Markdown to HTML on demand and cache the result automatically.

**How to enable:**

Pass the `--markdown-converter-command` flag when starting the server. Use `#INPUT#` as a placeholder for the Markdown source file and `#OUTPUT#` for the generated HTML file.

**Example using [Pandoc](https://pandoc.org/):**

```bash
./vibelog start --port 8080 --root-password secret \
  --markdown-converter-command 'pandoc --from markdown --to html --standalone --output #OUTPUT# #INPUT#'
```

**Caching behavior:**

- VibeLog generates a SHA-256 hash of each `.md` file based on its last modification time.
- The converted HTML is stored in `.vibelog_cache/markdown_cache/<sha>.html`.
- If the Markdown file has not changed since the last conversion, the cached HTML is served directly without re-running the converter.
- The cache directory can be changed with `--cache-dir` (default: `.vibelog_cache`).

### 2. Synchronization (Upload/Download)
Manage specific resources using dedicated commands. All commands require `--url` and `--root-password`. The `--database-path` is optional (default: `./database`).

**Available Commands:**
*   `upload-articles` / `download-articles`
*   `upload-authors` / `download-authors`
*   `upload-metrics` / `download-metrics`
*   `upload-config` / `download-config`

**Example: Upload Articles**
```bash
./vibelog upload-articles --url http://remote-server:8080 --root-password secret_pass
```

**Example: Download Config**
```bash
./vibelog download-config --url http://remote-server:8080 --root-password secret_pass
```

---

## Creating Content

### 1. Articles
Articles are stored in `database/articles/YYYY/MM/DD/<article_id>/`.

**Structure:**
*   `data.json`: Metadata (title, summary, tags).
*   `content.html`: The HTML body of the article.
*   `content.md`: Markdown source (alternative to `content.html`, requires `--markdown-converter-command`).
*   `assets/thumbnail.jpg`: Cover image.

**Example `data.json`:**
```json
{
    "title": "My New Article",
    "summary": "A short summary for the card view.",
    "author_id": "author_folder_name",
    "thumbnail": "assets/thumbnail.jpg",
    "categories": ["tech", "tutorial"]
}
```

### 2. Authors
Authors are stored in `database/authors/<author_id>/`.

**Structure:**
*   `data.json`: Profile info.
*   `assets/picture.jpg`: Profile picture.

**Example `data.json`:**
```json
{
    "name": "Jane Doe",
    "description": "Tech enthusiast and writer.",
    "picture": "assets/picture.jpg"
}
```

### 3. Categories
Edit `database/categorys.json` to manage categories globally.

**Example:**
```json
[
    {
        "name": "Tech",
        "navbar": true,
        "description": "Technology articles"
    }
]
```

---

## Database Structure

The project relies on a strict filesystem hierarchy:

```
database/
├── config/                 # Configuration & Assets
│   ├── categorys.json      # Global category definitions
│   ├── style.css           # Global styles
│   └── about.html          # About page content
├── articles/               # Article content
│   └── YYYY/
│       └── MM/
│           └── DD/
│               └── <article_id>/
│                   ├── data.json
│                   ├── content.html
│                   └── assets/thumbnail.jpg
├── authors/                # Author profiles
│   └── <author_id>/
│       ├── data.json
│       └── assets/picture.jpg
├── metrics/                # View analytics (auto-generated)
└── pages/                  # (Empty/Deprecated)
```

For detailed schema specifications, see [prompts/2.project.md](prompts/2.project.md).

---

## Development History

This project was built using **Cortex**, a C sandbox template for LLM-driven development.

*   **Original Template**: [Cortex on GitHub](https://github.com/VoidLayer9/Cortex)
*   **Prompt Engineering**: The project specifications and generation prompts are available in the `prompts/` directory:
    *   [`prompts/1.database_creation.md`](prompts/1.database_creation.md): Initial database population plan.
    *   [`prompts/2.project.md`](prompts/2.project.md): Full project specification and design document.
