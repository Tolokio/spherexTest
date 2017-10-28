#include "../../sphere/threads.h"
#include "CCrypto.h"

// Encryption used when logging in, to access the server list
void CCrypto::DecryptLogin( byte * pOutput, const byte * pInput, size_t iLen  )
{
	ADDTOCALLSTACK("CCrypto::DecryptLogin");
	if ( GetClientVer() >= 0x125370 )
	{
		for ( size_t i = 0; i < iLen; i++ )
		{
			pOutput[i] = pInput[i] ^ (byte) m_CryptMaskLo;
			dword MaskLo = m_CryptMaskLo;
			dword MaskHi = m_CryptMaskHi;
			m_CryptMaskLo = ((MaskLo >> 1) | (MaskHi << 31)) ^ m_MasterLo;
			MaskHi = ((MaskHi >> 1) | (MaskLo << 31)) ^ m_MasterHi;
			m_CryptMaskHi = ((MaskHi >> 1) | (MaskLo << 31)) ^ m_MasterHi;
		}
		return;
	}

	if ( GetClientVer() == 0x125360 )
	{
		for ( size_t i = 0; i < iLen; i++ )
		{
			pOutput[i] = pInput[i] ^ (byte) m_CryptMaskLo;
			dword MaskLo = m_CryptMaskLo;
			dword MaskHi = m_CryptMaskHi;
			m_CryptMaskHi =
				(m_MasterHi >> ((5 * MaskHi * MaskHi) & 0xff))
				+ (MaskHi * m_MasterHi)
				+ (MaskLo * MaskLo * 0x35ce9581)
				+ 0x07afcc37;
			m_CryptMaskLo =
				(m_MasterLo >> ((3 * MaskLo * MaskLo) & 0xff))
				+ (MaskLo * m_MasterLo)
				- (m_CryptMaskHi * m_CryptMaskHi * 0x4c3a1353)
				+ 0x16ef783f;
		}
		return;
	}

	if ( GetClientVer() ) // CLIENT_VER <= 0x125350
	{
		for ( size_t i = 0; i < iLen; i++ )
		{
			pOutput[i] = pInput[i] ^ (byte) m_CryptMaskLo;
			dword MaskLo = m_CryptMaskLo;
			dword MaskHi = m_CryptMaskHi;
			m_CryptMaskLo = ((MaskLo >> 1) | (MaskHi << 31)) ^ m_MasterLo;
			m_CryptMaskHi = ((MaskHi >> 1) | (MaskLo << 31)) ^ m_MasterHi;
		}
		return;
	}

	if ( pOutput != pInput )
	{
		memcpy( pOutput, pInput, iLen );
	}
}