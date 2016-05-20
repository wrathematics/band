#' Arithmetic Operators
#' 
#' Binary operations for banded/banded, banded/matrix, and banded/vector
#' operations.
#' 
#' @details
#' If \code{e1} and \code{e2} are banded matrices, then they must be
#' conformable and packed in the same way.
#' 
#' @param e1,e2
#' Banded matrices or numeric vectors
#' 
#' @return
#' A banded matrix.
#' 
#' @name arithmetic
#' @rdname arithmetic
#' @keywords Methods
NULL



check_arith <- function(e1, e2)
{
  if (any(getdim(e1) != getdim(e2)))
    stop("dimensions of band matrices disagree")
  if (any(kdim(e1) != kdim(e2)))
    stop("bandwidths of band matrices are non-conformable")
}



#' @rdname arithmetic
#' @export
setMethod("*", signature(e1="BandMat", e2="BandMat"), 
  function(e1, e2)
  {
    check_arith(e1, e2)
    if (class(e1) == "ZeroMat" || class(e2) == "ZeroMat")
      return(zeromat(e1@dim))
    
    setData(e1) <- getData(e1) * getData(e2)
    return(e1)
  }
)



#' @rdname arithmetic
#' @export
setMethod("*", signature(e1="BandMat", e2="numeric"), 
  function(e1, e2)
  {
    if (length(e2) != 1)
      stop("only a length 1 numeric vector can be used with a banded matrix at this time")
    
    if (isTRUE(all.equal(e2, 0)))
      ret <- zeromat(getdim(e1))
    else if (isTRUE(all.equal(e2, 1)))
      ret <- e1
    else
      ret <- getData(e1) * e2
    
    return(ret)
  }
)



#' @rdname arithmetic
#' @export
setMethod("*", signature(e1="numeric", e2="BandMat"), 
  function(e1, e2)
    return(e2*e1)
)
