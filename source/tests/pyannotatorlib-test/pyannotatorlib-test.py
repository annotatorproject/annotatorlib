import os
import sys
sys.path.append(os.getcwd())
import pyannotatorlib as annotator
f = annotator.Frame(42)
c = annotator.Class("superclass")
o = annotator.Object(c)
a = annotator.Annotation.construct(f, o)
print(a.get_frame().get_id())
