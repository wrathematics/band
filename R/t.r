#' t
#' 
#' @param x
#' A banded matrix.
#' 
#' @return
#' A banded matrix of the same type.
#' 
#' @keywords LinAlg
#' @name xpose
#' @rdname xpose
NULL

xpose_BandMat <- function(x)
{
  dim <- getdim(x)
  k <- kdim(x)
  
  out <- .Call(R_xpose_band, getData(x), dim[1L], dim[2L], k[1L], k[2L])
  genbandmat(out, rev(dim), k[2L], k[1L])
}

xpose_err <- function(x)
{
  if (class(x) == "ZeroMat")
    nm <- "zero"
  else if (class(x) == "DiagMat")
    nm <- "diagonal"
  else if (class(x) == "SymMat")
    nm <- "symmetric"
  
  stop(paste("a", nm, "matrix is its own transpose"))
}

#' @rdname xpose
#' @export
setMethod("t", signature(x="BandMat"), xpose_err)

#' @rdname xpose
#' @export
setMethod("t", signature(x="GenBandMat"), xpose_BandMat)

#' @rdname xpose
#' @export
setMethod("t", signature(x="SymMat"), xpose_err)

#' @rdname xpose
#' @export
setMethod("t", signature(x="matrix"), 
  function(x)
  {
    dims <- dim(x)
    if (any(dims == 1L))
    {
      dim(x) <- rev(dims)
      return(x)
    }
    
    .Call(R_xpose_full, x)
  }
)
