# PYTHON

## Build

```bash
cd build
cmake -DOPTION_BUILD_PYTHON=1 ..
make
```

## Examples

### Load Project

```python
import pyannotatorlib as pan
pan.load_imagesets("imagesets")
pan.load_storages("storages")
project = pan.Project.load_path("annotator.pro.xml")
imageset = project.get_imageset()
storage = project.get_storage()
session = project.get_session()
```

### Show Images

```python
import pyannotatorlib as pan
from matplotlib import pyplot as plt
pan.load_imagesets("imagesets")
pan.load_storages("storages")
project = pan.Project.load_path("annotator.pro.xml")
imageset = project.get_imageset()
img = imageset.get_image(42)
plt.imshow(img)
plt.show()
```