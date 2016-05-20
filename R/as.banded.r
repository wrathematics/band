#' as.banded
#' 
#' Convert a regular R matrix into a banded matrix.
#' 
#' @details
#' The values \code{kl} and \code{ku} describe the bandwidth of the band
#' matrix.  If they are different, they will produce a general banded
#' matrix.  If they are both 0, they will produce a diagonal matris.
#' 
#' @param x
#' A matrix containing numeric, integer, or logical data.
#' @param kl,ku
#' The size of the lower and upper bands.  See the details section for more
#' information.  Each should be a non-negative integer.
#' 
#' @return
#' A banded matrix.
#' 
#' @seealso \code{\link{kdim}} and \code{\link{classes}}
#' 
#' @export
as.banded <- function(x, kl, ku) ## TODO symmetric
{
  if (!is.matrix(x))
    stop("argument 'x' must be a matrix")
  if (!is.numeric(x) && !is.logical(x))
    stop("argument 'x' must contain numeric, integer, or logical data")
  
  if (missing(kl) && missing(ku))
    stop("must supply at least one of 'kl' or 'ku'")
  else if (missing(kl))
    kl <- ku
  else if (missing(ku))
    ku <- kl
  
  dim <- dim(x)
  
  if (ku > dim[1L] || kl > dim[1L])
    stop("'ku' and 'kl' must each be smaller than nrow(x)")
  if (max(ku, kl) > min(dim))
    warning("banded storage schemes are only practical if kl, ku << min(dim(x))")
  
  ku <- as.integer(ku)
  kl <- as.integer(kl)
  
  out <- .Call(R_tobanded, x, kl, ku)
  
  if (kl == 0L && ku == 0L)
    ret <- new("DiagMat", Data=out, dim=dim)
  else
    ret <- new("GenBandMat", Data=out, dim=dim, kl=kl, ku=ku)
  
  ret
}
