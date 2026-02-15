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

Download the latest pre-compiled version for your platform from the [Releases page](https://github.com/VoidLayer9/VibeLog/releases/tag/0.0.2).

### Build from Source

1. **Clone the Repository**
   ```bash
   git clone https://github.com/your-username/vibelog.git
   cd vibelog
   ```

2. **Compile**
   Use standard GCC or Clang:
   ```bash
   gcc app.c -o vibelog
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
./vibelog start --port 8080 --database-path ./database --root-password secret_pass
```

*   `--port`: Port to listen on (default: 8080).
*   `--database-path`: Path to the database folder (required).
*   `--root-password`: Admin password for API operations (required).

### 2. Upload Content (Sync Up)
Upload a local file or directory to a remote VibeLog instance:

```bash
./vibelog upload --path database/articles/new-post --url http://remote-server:8080 --root-password secret_pass
```

*   `--path`: Local path to upload.
*   `--url`: URL of the remote server.
*   `--root-password`: Must match the remote server's password.

### 3. Download Content (Sync Down)
Download files from a remote instance to your local environment:

```bash
./vibelog download --path database --url http://remote-server:8080 --root-password secret_pass
```

---

## Creating Content

### 1. Articles
Articles are stored in `database/articles/DD-MM-YYYY/<article_id>/`.

**Structure:**
*   `data.json`: Metadata (title, summary, tags).
*   `content/en.html`: The HTML body of the article.
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
├── categorys.json          # Global category definitions
├── articles/               # Article content
│   └── DD-MM-YYYY/
│       └── <article_id>/
│           ├── data.json
│           ├── content/en.html
│           └── assets/thumbnail.jpg
├── authors/                # Author profiles
│   └── <author_id>/
│       ├── data.json
│       └── assets/picture.jpg
├── metrics/                # View analytics (auto-generated)
└── pages/                  # Static pages (e.g., about.html)
```

For detailed schema specifications, see [prompts/2.project.md](prompts/2.project.md).

---

## Development History

This project was built using **Cortex**, a C sandbox template for LLM-driven development.

*   **Original Template**: [Cortex on GitHub](https://github.com/VoidLayer9/Cortex)
*   **Prompt Engineering**: The project specifications and generation prompts are available in the `prompts/` directory:
    *   [`prompts/1.database_creation.md`](prompts/1.database_creation.md): Initial database population plan.
    *   [`prompts/2.project.md`](prompts/2.project.md): Full project specification and design document.
