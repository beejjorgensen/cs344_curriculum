## HOW TO

All the Markdown stuff here is for Canvas.

Start all top-level headers for Canvas with `##` (header 2).

VS Code preview sadly doesn't copy out the `<pre>` attribute for code
blocks in a way that Canvas understands.

Install `cmark-gfm` and `make` to build the `.html` files. You can paste
the HTML files into the Canvas HTML editor.

`make clean` to get rid of the `.html` files.

## Gotchas

* After pasting, look at the Canvas accessibility checker to see if
  there's anything that needs fixing (i.e. table captions).

* The quizzes have to be pasted in a line at once. Bummer.
