#include "StdInc.h"

void CCompressedMatrixNotAligned::InjectHooks()
{
    Install("CCompressedMatrixNotAligned", "DecompressIntoFullMatrix", 0x59B9F0, &CCompressedMatrixNotAligned::DecompressIntoFullMatrix);
    Install("CCompressedMatrixNotAligned", "CompressFromFullMatrix", 0x59BAD0, &CCompressedMatrixNotAligned::CompressFromFullMatrix);
}

void CCompressedMatrixNotAligned::DecompressIntoFullMatrix(CMatrix& matrix)
{
    matrix.GetRight() = m_vecRight.Decompress();
    matrix.GetForward() = m_vecForward.Decompress();
    matrix.GetUp() = CrossProduct(matrix.GetRight(), matrix.GetForward());
    matrix.GetPosition() = m_vecPos;
    matrix.Reorthogonalise();
}

void CCompressedMatrixNotAligned::CompressFromFullMatrix(CMatrix& matrix)
{
    m_vecRight = matrix.GetRight();
    m_vecForward = matrix.GetForward();
    m_vecPos = matrix.GetPosition();
}

