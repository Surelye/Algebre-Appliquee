(TeX-add-style-hook
 "example-work"
 (lambda ()
   (TeX-add-to-alist 'LaTeX-provided-class-options
                     '(("SCWorks" "bachelor" "och" "pract4" "times" "hidelinks")))
   (TeX-add-to-alist 'LaTeX-provided-package-options
                     '(("fontenc" "T2A") ("inputenc" "cp1251") ("cite" "sort" "compress") ("babel" "english" "russian") ("hyperref" "colorlinks=false")))
   (add-to-list 'LaTeX-verbatim-environments-local "VerbatimOut")
   (add-to-list 'LaTeX-verbatim-environments-local "SaveVerbatim")
   (add-to-list 'LaTeX-verbatim-environments-local "LVerbatim*")
   (add-to-list 'LaTeX-verbatim-environments-local "LVerbatim")
   (add-to-list 'LaTeX-verbatim-environments-local "BVerbatim*")
   (add-to-list 'LaTeX-verbatim-environments-local "BVerbatim")
   (add-to-list 'LaTeX-verbatim-environments-local "Verbatim*")
   (add-to-list 'LaTeX-verbatim-environments-local "Verbatim")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "href")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "hyperref")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "hyperimage")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "hyperbaseurl")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "nolinkurl")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "url")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "path")
   (add-to-list 'LaTeX-verbatim-macros-with-delims-local "path")
   (add-to-list 'LaTeX-verbatim-macros-with-delims-local "Verb*")
   (add-to-list 'LaTeX-verbatim-macros-with-delims-local "Verb")
   (TeX-run-style-hooks
    "latex2e"
    "SCWorks"
    "SCWorks10"
    "fontenc"
    "inputenc"
    "graphicx"
    "cite"
    "amsmath"
    "amssymb"
    "amsthm"
    "fancyvrb"
    "longtable"
    "array"
    "babel"
    "tempora"
    "hyperref")
   (TeX-add-symbols
    "eqdef")
   (LaTeX-add-amsthm-newtheorems
    "lem"))
 :latex)

