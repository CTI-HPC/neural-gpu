# -*- coding: utf-8 -*-

import sys, os
from os.path import abspath

sys.path.insert(0, abspath('.'))
sys.path.insert(0, abspath('_modules'))

templates_path = ['_templates']
exclude_patterns = ['_build', 'disqus.rst']

extensions = [
    'sphinx.ext.jsmath',
]

jsmath_path = 'jsMath/easy/load.js'


source_suffix = '.rst'
master_doc = 'index'
default_role = 'math'
highlight_language = 'c'

project = u'Seminario GPU'
copyright = u'2012, CTI-HPC'
version = '1'
release = '1'
language = 'es'

pygments_style = 'sphinx'

html_static_path = ['_static']
html_theme_path = ['_theme']

html_theme = 'progra'
html_theme_options = {
    'nosidebar': True,
}

html_title = u'Seminario GPU'
html_short_title = u'Seminario GPU'

html_use_modindex = False
html_use_index = True

htmlhelp_basename = 'SeminarioGPU'

latex_documents = [
  ('index', 'seminario-gpu.tex', u'Seminario GPU',
   u'CTI-HPC', 'manual'),
]

latex_elements = {
    'fontpkg': '\\usepackage{mathpazo}',
    'pointsize': '12pt',
    #'preamble': '\\usepackage[spanish]{babel} \selectlanguage{spanish}',
}

man_pages = [
    ('index', 'seminario-gpu', u'Seminario GPU',
     [u'CTI-HPC'], 1)
]
