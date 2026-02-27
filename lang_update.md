# Lang Refactor — Especificação de Implementação

## Estado Atual

- Banco de dados já organizado por lang: `database/<lang>/articles`, `database/<lang>/authors`, etc.
- Rotas atuais sem prefixo de lang: `/`, `/list_articles`, `/article`, `/author`, `/about`
- CLI de sync usa URL sem lang: `--url http://server:8080`
- `global_config.database_path` aponta direto para a raiz (ex: `database/`), sem separar por lang

## Objetivo

Todas as rotas públicas devem ter prefixo de lang. O código deve ler os dados do subdiretório correspondente à lang da rota.

---

## 1. Novas Rotas HTTP

| Rota atual           | Nova rota               |
|----------------------|-------------------------|
| `GET /`              | `GET /<lang>/`          |
| `GET /list_articles` | `GET /<lang>/list_articles` |
| `GET /article`       | `GET /<lang>/article`   |
| `GET /author`        | `GET /<lang>/author`    |
| `GET /about`         | `GET /<lang>/about`     |

Rotas de API (`/api/*`) e utilitárias (`/database_file`, `/favicon.ico`) **não** ganham prefixo de lang.

A rota raiz `/` deve redirecionar para `/<default_lang>/` (default: `en`).

### Extração da lang

No router, extrair a lang do caminho da rota:

```c
// Dado: route = "/<lang>/<sub_route>"
// Extrair lang: tudo entre o primeiro '/' e o segundo '/'
// Extrair sub_route: tudo após o segundo '/'
```

Lang válida: qualquer string sem `/`. Exemplos: `en`, `pt`, `es`.

### Resolução do database path por lang

Para cada request com lang, o caminho efetivo do banco de dados é:

```c
char *lang_db_path = concat_path(global_config.database_path, lang);
// ex: "database/en"
```

Todos os handlers (`handle_home`, `handle_list_articles`, `handle_article`, `handle_author`, `handle_about`) devem receber e usar `lang_db_path` em vez de `global_config.database_path` diretamente.

O cache de `cached_categories` e `cached_text_config` deve ser **por lang** (usar map ou invalidar ao trocar de lang).

### Links gerados no HTML

Todos os links gerados dinamicamente no `render_page` e handlers devem incluir o prefixo `/<lang>/`:

```c
// Antes:
d->ctext_append(t, "<a href='/list_articles?...'>");
// Depois:
d->ctext_append(t, "<a href='/");
d->ctext_append(t, lang);
d->ctext_append(t, "/list_articles?...'>");
```

---

## 2. CLI — Comandos de Sync

Os comandos de sync (`upload-articles`, `download-articles`, etc.) devem aceitar a URL **com a lang embutida**:

```bash
# Antes:
vibelog upload-articles --url http://vibelog.mateusmoutinho.com --root-password secret

# Depois:
vibelog upload-articles --url http://vibelog.mateusmoutinho.com/en --root-password secret
```

### Extração da lang da URL

Ao receber `--url`, extrair a lang do path da URL:

```
http://vibelog.mateusmoutinho.com/en  →  lang = "en"
http://vibelog.mateusmoutinho.com/pt  →  lang = "pt"
http://localhost:8080/en              →  lang = "en"
```

A `url_base` para as chamadas de API deve ser a URL **sem** o path de lang:

```
url_base = "http://vibelog.mateusmoutinho.com"
lang     = "en"
```

### sub_path com lang

O `sub_path` passado para `perform_upload_sync` / `perform_download_sync` deve incluir a lang:

```c
// Antes:
target_sub = "articles";

// Depois:
// montar: "<lang>/articles"  →  ex: "en/articles"
char sub_with_lang[64];
snprintf(sub_with_lang, sizeof(sub_with_lang), "%s/%s", lang, target_sub);
```

Isso faz com que o sync leia/escreva em `database/<lang>/articles`, correspondendo à estrutura real do banco.

---

## 3. Resumo das Mudanças em `app.c`

1. **Router** (`router`): extrair `lang` e `sub_route` da rota. Despachar handlers com `lang`.
2. **Handlers**: receber `lang` como parâmetro, resolver `lang_db_path = database_path + "/" + lang`.
3. **Cache**: tornar `cached_categories` e `cached_text_config` sensíveis à lang (ou simplificar invalidando por request).
4. **Links HTML**: injetar `/<lang>/` em todos os hrefs gerados.
5. **`appmain`** (CLI): extrair lang da URL fornecida via `--url`, montar `sub_path` como `<lang>/<tipo>`.
6. **Redirect `/`**: retornar redirect 302 para `/en/` (ou lang padrão configurável).
