import numpy as np
import array_to_latex as a2l
from hamming3d import G as hamming3d_G, H as hamming3d_H
from hamming import G as hamming_G, H_transpose as hamming_H

a2l.to_ltx(hamming3d_G, frmt='{:1.0f}', arraytype='matrix')

