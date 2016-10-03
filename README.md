# band

* **Version:** 0.1-0
* **Status:** [![Build Status](https://travis-ci.org/wrathematics/band.png)](https://travis-ci.org/wrathematics/band)
* **License:** [![License](http://img.shields.io/badge/license-BSD%202--Clause-orange.svg?style=flat)](http://opensource.org/licenses/BSD-2-Clause)
* **Author:** Drew Schmidt


An R package for packed matrix storage, including banded, symmetric, and diagonal matrices.

In addition to a few virtual classes, we offer the following S4 classes:

| Class      | Description  |
|------------|------------- |
| ZeroMat    | A zero matrix. Only dimension information is stored. | 
| DiagMat    | Diagonal matrices. Only the diagonal entries are stored. |
| GenBandMat | A general band storage matrix. Only the band elements are stored. |
| SymMat     | Packed symmetric (not band) storage.  Only one triangle (+ diagonal) is stored. |

The list of currently implemented methods is:

| Description | Functions |
|-------------|---------- |
| Casters | `as.banded()`, `as.matrix()`, `as.symmetric()` |
| Checks | `isSym()` | 
| Transpose | `xpose()` |

Note that attempting to transpose a zero, diagonal, or symmetric matrix will produce an error *because these are already their own transpose* and there is no good reason to create a copy.

Finally, we include optimized versions of `xpose()` and `isSym()` for regular R matrices.



## Installation

<!-- To install the R package, run:

```r
install.package("band")
``` -->

The development version is maintained on GitHub, and can easily be installed by any of the packages that offer installations from GitHub:

```r
### Pick your preference
devtools::install_github("wrathematics/band")
ghit::install_github("wrathematics/band")
remotes::install_github("wrathematics/band")
```





## Package Use

TODO
