#' @title Print \code{BandMat} objects
#' @description Printing for \code{BandMat} objects.
#' @param x \code{BandMat} object
#' @param ... unused
#' @name print-BandMat
#' @rdname print-Bandmat
#' @method print BandMat
#' @export
print.BandMat <- function(x, ...)
{
  dim <- getdim(x)
  k <- kdim(x)
  
  .Call(R_matprinter, getData(x), dim[1L], dim[2L], k[1L], k[2L])
  invisible()
}
