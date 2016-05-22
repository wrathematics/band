#' isSymmetric
#' 
#' Test if a matrix is symmetric.
#' 
#' @param object
#' A matrix-like object.
#' 
#' @param ...
#' Ignored.
#' 
#' @return
#' \code{TRUE} or \code{FALSE}, accordingly.
#' 
#' @name isSymmetric
#' @rdname isSymmetric
NULL

dimcheck <- function(object, ...)
{
  dim <- getdim(object)
  if (dim[1L] != dim[2L])
    FALSE
  else
    TRUE
}

#' @rdname isSymmetric
#' @export
setMethod("isSymmetric", signature(object="DiagMat"), dimcheck)

#' @rdname isSymmetric
#' @export
setMethod("isSymmetric", signature(object="ZeroMat"), dimcheck)

#' @rdname isSymmetric
#' @export
setMethod("isSymmetric", signature(object="SymMat"), dimcheck)

#' @rdname isSymmetric
#' @export
setMethod("isSymmetric", signature(object="GenBandMat"),
  function(object, ...)
  {
    dim <- getdim(object)
    if (dim[1L] != dim[2L])
      return(FALSE)
    k <- kdim(object)
    if (k[1L] != k[2L])
      return(FALSE)
    
    .Call(R_is_symmetric, getData(object), dim[1L], k[1L])
  }
)
