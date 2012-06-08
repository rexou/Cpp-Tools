//==========================================================
// Plugin.inl
//
// Implantation de la classe CPlugin
//
//==========================================================


////////////////////////////////////////////////////////////
// Constructeur par d�faut
//
////////////////////////////////////////////////////////////
template <class T>
inline CPlugin<T>::CPlugin() :
m_Library(NULL)
{

}


////////////////////////////////////////////////////////////
// Destructeur
//
////////////////////////////////////////////////////////////
template <class T>
inline CPlugin<T>::~CPlugin()
{
    if (m_Library)
        FreeLibrary(m_Library);
}


////////////////////////////////////////////////////////////
// Charge la DLL et r�cup�re un pointeur sur l'objet
//
// [in] Filename : Chemin de la DLL
//
// [retval] Pointeur sur l'objet cr�� par la DLL
//
////////////////////////////////////////////////////////////
template <class T>
inline T* CPlugin<T>::Load(const std::string& Filename)
{
    // Chargement de la biblioth�que dynamique
    m_Library = LoadLibrary(Filename.c_str());
    if (!m_Library)
        throw CLoadingFailed(Filename, "Impossible de charger la biblioth�que dynamique");

    // R�cup�ration de la fonction
    PtrFunc Function = reinterpret_cast<PtrFunc>(GetProcAddress(m_Library, "StartPlugin"));
    if (!Function)
        throw CLoadingFailed(Filename, "Impossible de trouver la fonction 'StartPlugin' dans la biblioth�que dynamique");

    return Function();
}
