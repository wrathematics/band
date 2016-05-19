library(band)

### Diagonal band
x <- matrix(1:100, 10, 10)

truth <- diag(x)
band <- as.banded(x, 0, 0)
test <- band@Data
stopifnot(all.equal(truth, test))

truth <- diag(diag(x))
test <- as.matrix(band)
stopifnot(all.equal(truth, test))

# double
storage.mode(x) <- "double"

truth <- diag(x)
band <- as.banded(x, 0, 0)
test <- band@Data
stopifnot(all.equal(truth, test))

truth <- diag(diag(x))
test <- as.matrix(band)
stopifnot(all.equal(truth, test))

### 
