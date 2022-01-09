## HOWTO

All the Markdown stuff here is for Canvas.

Start all top-level headers for Canvas with `##` (header 2).

The easiest way to get it in is to load it in VS Code and open the
Markdown preview. Then cut and paste the preview into Canvas's rich
editor.

It should paste is without a hitch.

## Future directions

Other options are to process the files with something like `cmark` or
`cmark-gfm` into HTML and upload those into Canvas's HTML editor.

That's an extra step, but it gives us the opportunity to process the
HTML entities with `style=` attributes, add headers and footers, etc.