//==========================================================
// Plugin.inl
//
// Implantation de la classe CPlugin
//
//==========================================================


////////////////////////////////////////////////////////////
// Constructeur par défaut
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
// Charge la DLL et récupère un pointeur sur l'objet
//
// [in] Filename : Chemin de la DLL
//
// [retval] Pointeur sur l'objet créé par la DLL
//
////////////////////////////////////////////////////////////
template <class T>
inline T* CPlugin<T>::Load(const std::string& Filename)
{
    // Chargement de la bibliothèque dynamique
    m_Library = LoadLibrary(Filename.c_str());
    if (!m_Library)
        throw CLoadingFailed(Filename, "Impossible de charger la bibliothèque dynamique");

    // Récupération de la fonction
    PtrFunc Function = reinterpret_cast<PtrFunc>(GetProcAddress(m_Library, "StartPlugin"));
    if (!Function)
        throw CLoadingFailed(Filename, "Impossible de trouver la fonction 'StartPlugin' dans la bibliothèque dynamique");

    return Function();
}
